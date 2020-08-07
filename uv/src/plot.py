import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

class UVTube:

    def __init__(self, length, height, sections, intensity, x_start, speed):
        self.length_ = length
        self.height_ = height
        self.sections_ = int(sections)
        self.intensity_ = intensity
        self.speed_ = speed
        self.x_ = x_start                               # horizontal position
        self.y_ = np.arange(start=height, stop=length+height, step=length/sections, dtype=np.float)

    def move(self, dt):
        self.x_ = self.x_ + self.speed_*dt

class Wall:

    def __init__(self, length, height, mesh_size, dist_to_wall, init_dose):
        self.length_ = length
        self.height_ = height
        self.mesh_size_ = mesh_size
        self.n_x_ = int(length/mesh_size)
        self.n_y_ = int(height/mesh_size)
        self.z_ = 2.0
        self.distribution = np.full((self.n_y_, self.n_x_), init_dose, dtype=np.float)

    def calcDist(self, tube_x, tube_y, i, j, z):
        x = i*self.mesh_size_ - tube_x
        y = j*self.mesh_size_ - tube_y
        dist = np.sqrt(x*x + y*y + z*z)
        return dist

    def recieveDose(self, tube, dt):
        for tube_y in tube.y_:
            for i in range(0, self.n_y_):
                for j in range(0, self.n_x_):
                    dist = self.calcDist(tube.x_, self.height_-tube_y, j, i, self.z_)
                    I = tube.intensity_/tube.sections_/(dist*dist)
                    self.distribution[i][j] = self.distribution[i][j] + I*dt


def main():
    print("Running Simulation...")
    wall_length = 5.0
    wall_height = 3.0
    wall_mesh_size = 0.1
    dist_to_wall = 2.0
    init_dose = -25.0

    tube_length = 1.0
    tube_height = 0.65
    tube_n_sections = 10
    tube_intensity = 1.83
    tube_speed = 0.05

    dt = 0.1
    x_start = 0.0
    x_end = 5.0

    wall = Wall(wall_length, wall_height, wall_mesh_size, dist_to_wall, init_dose)
    tube = UVTube(tube_length, tube_height, tube_n_sections, tube_intensity, x_start, tube_speed)

    fig, ax = plt.subplots()
    ax.set_xlabel('Wall width (x0.1m)')
    ax.set_ylabel('Wall height (x0.1m)')
    ax.set_title('Total Dose Recieved by the Wall (mJ)')
    ims = []

    while tube.x_ <= x_end:
        wall.recieveDose(tube, dt)
        tube.move(dt)

        im = ax.imshow(wall.distribution, cmap='hot', interpolation='nearest', animated=True)
        ims.append([im])
    
    ani = animation.ArtistAnimation(fig, ims, interval=50, repeat_delay=1000, blit=True)
    plt.show()

if __name__ == "__main__":
    main()
