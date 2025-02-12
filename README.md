# ROS Workspace - `ros_ws`

This is a ROS Noetic workspace for developing and testing robotic applications.

## 📌 Project Structure

```
ros_ws/ 
│── src/ # Source code for ROS packages
│── build/ # Build directory (ignored in Git)
│── devel/ # Development space (ignored in Git)
│── install/ # Install space (optional)
│── CMakeLists.txt # CMake entry point for the workspace
│── README.md # This file
```


## 🚀 How to Use

### 1️⃣ Clone the Repository
```sh
git clone git@github.com:aromal-path/ros_ws.git
cd ros_ws
```

2️⃣ Initialize & Build

```sh
catkin build
source devel/setup.bash
```

3️⃣ Running Nodes
#### From a terminal, with `devel/setup.bash` properly sourced as above, launch the `add_two_ints` server node
  - This will implicitly start `roscore` if not running.
  - This node will keep running in the terminal listening for service calls till it is killed by `ctrl+c`.

```sh
roslaunch my_robot_package add_two_ints.launch
```

#### From another terminal, with `devel/setup.bash` properly sourced as above, run the `add_two_ints` client node
  - This will run once, calls the server, prints the result and exit.
  - This can be repeated, passing in different numbers to add.

```sh
ROS_NAMESPACE=/my_robot rosrun my_robot_package add_two_ints_client 100 5
```

#### Launch the `test_params` node
  - This will run once, prints the parameter values and exit.
  - This can be repeated.

```sh
roslaunch my_robot_package test_params.launch
```

🔧 Dependencies
  - Ubuntu 20.04
  - ROS Noetic
  - Catkin Tools

💡 Contributing
  1. Fork this repository
  2. Create a new branch: git checkout -b feature-branch
  3. Make changes and commit: git commit -m "Add new feature"
  4. Push to your fork: git push origin feature-branch
  5. Open a Pull Request

📜 License
This project is licensed under the MIT License.