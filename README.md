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
Launch the `add_two_ints` server node (this will implicitly start `roscore` if not running):

```sh
roslaunch my_robot_package add_two_ints.launch
```

Run the `add_two_ints` client node (this will run once, calls the server, prints the result and exit):

```sh
ROS_NAMESPACE=/my_robot rosrun my_robot_package add_two_ints_client 100 5
```

Launch the `test_params` node (this will run once, prints the parameter values and exit):

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