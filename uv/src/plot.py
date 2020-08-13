import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

class UVTube:

    def __init__(self, length, height, sections, intensity, x_start, speed):
        self.length_ = length           # length of the tube [m]
        self.height_ = height           # height of the bottom of the tube from ground [m]
        self.sections_ = int(sections)  # number of sections that the tube is divided into
        self.intensity_ = intensity     # UV intensity (total) [J/s]
        self.speed_ = speed             # robot moving speed (in x direction) [m/s]
        self.x_ = x_start               # horizontal position of the tube [m]
        self.y_ = np.arange(start=height, stop=length+height, step=length/sections, dtype=np.float) # vertical position of each section[m]

    def move(self, dt: float):
        """
        Move the robot one step forward
        
        Parameters
        ----------
        `dt` : time step (delta) in float
        """
        self.x_ = self.x_ + self.speed_*dt

class Wall:

    def __init__(self, length: float, height: float, mesh_size: float, dist_to_wall: float, init_dose: float):
        self.length_ = length               # length of the wall in horizontal direction(x) [m]
        self.height_ = height               # length of the wall in vertical direction(y) [m]
        self.mesh_size_ = mesh_size         # the size of the meshes of the wall in both direction(x, y) [m]
        self.n_x_ = int(length/mesh_size)   # num of wall meshes in horizontal direction(x)
        self.n_y_ = int(height/mesh_size)   # num of wall meshes in vertical direction(y)
        self.z_ = 2.0                       # the normal distance from the robot to the wall [m]
        self.distribution = np.full((self.n_y_, self.n_x_), init_dose, dtype=np.float)  # 2D matrix containing the dosage at each wall mesh [J]
        self.vis = np.zeros((self.n_y_, self.n_x_), dtype=np.int)  # 2D matrix for visualization

    def calcDist(self, tube_x: float, tube_y: float, i: int, j: int, z: float) -> float:
        """
        Move the robot one step forward

        Parameters
        ----------
        `tube_x` : the location of this tube section in horizontal direction(x) in float [m]

        `tube_y` : the location of this tube section in vertical direction(y) in float [m]

        `i` : index of the wall mesh in horizontal direction(x) in int

        `j` : index of the wall mesh in vertical direction(y) in int

        `z` : the normal distance from this tube section to the wall in float [m]

        Return
        ----------
        `dist` : the euclidean distance from this tube section to the wall in float [m]
        """
        x = i*self.mesh_size_ - tube_x
        y = j*self.mesh_size_ - tube_y
        dist = np.sqrt(x*x + y*y + z*z)
        return dist

    def recieveDose(self, tube: UVTube, dt: float, dose_thresh: float):
        """
        Let the wall recieve UV dosage
        
        Parameters
        ----------
        `tube` : a instance of the class `UVTube` that interacts with this wall

        `dt` : time step (delta) in float [s]

        `dose_thresh` : threshold for dosage in float [mJ]
        """
        for tube_y in tube.y_:
            for i in range(0, self.n_y_):
                for j in range(0, self.n_x_):
                    dist = self.calcDist(tube.x_, self.height_-tube_y, j, i, self.z_)
                    I = tube.intensity_/tube.sections_/(dist*dist)
                    self.distribution[i][j] = self.distribution[i][j] + I*dt
                    if self.distribution[i][j] >= dose_thresh:
                        self.vis[i][j] = 1


def main():
    print("Simulation Started...")
    wall_length = 3.0
    wall_height = 3.0
    wall_mesh_size = 0.1
    dist_to_wall = 2.0
    init_dose = 0.0
    dose_thresh = 25.0

    tube_length = 1.0
    tube_height = 0.65
    tube_n_sections = 10
    tube_intensity = 1.83
    tube_speed = 0.04

    dt = 0.5                # time step [s]
    x_start = 0.0           # the starting position of the robot in horizontal direction(x) [m]
    x_end = 5.0             # the end position of the robot in horizontal direction(x) [m]

    # instanciate wall and tube
    wall = Wall(wall_length, wall_height, wall_mesh_size, dist_to_wall, init_dose)
    tube = UVTube(tube_length, tube_height, tube_n_sections, tube_intensity, x_start, tube_speed)

    # prepare plot
    fig, ax = plt.subplots()
    ax.set_xlabel('Wall width (x' + '%.2f' % wall_mesh_size + ' m)')
    ax.set_ylabel('Wall height (x' + '%.2f' % wall_mesh_size + ' m)')
    # ax.set_title('Total Dose Recieved by the Wall (mJ)')
    ims = []

    t = 0.0 # time [s]
    while tube.x_ <= x_end:
        # run the simulation
        t += dt           # the starting position of the robot in horizontal direction(x) [m]
        wall.recieveDose(tube, dt, dose_thresh)
        tube.move(dt)

        # add the current frame to the animation
        # im = ax.imshow(wall.distribution, cmap='hot', interpolation='nearest', animated=True)
        ax.set_title('Total Dose Recieved by the Wall (mJ)' + ' at t = ' + '%.1f' % t + " s")
        im = ax.imshow(wall.vis, animated=True)
        ims.append([im])
        
        # print current progress in percentage
        msg = "Progress: " + "%d" % int((tube.x_-x_start)/(x_end-x_start)*100) + "% "
        print(msg, end="\r")
    
    # display the animation
    ani = animation.ArtistAnimation(fig, ims, interval=50, repeat_delay=1000, blit=True)
    plt.show()

    # save the animation
    print("Saving to gif file...")
    ani.save('animation.gif', writer='imagemagick', fps=30)
    print("Done!")

if __name__ == "__main__":
    main()
