
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    launch_description = LaunchDescription()

    turtle_simulator = Node(
        package="turtlesim",
        executable="turtlesim_node",
    )
    launch_description.add_action(turtle_simulator)

    turtle_spawner = Node(
        package="turtlesim_catch_them_all",
        executable="turtle_spawner_node",
        parameters=[
            {"spawn_frequency": 4}
        ],
    )
    launch_description.add_action(turtle_spawner)

    turtle_controller = Node(
        package="turtlesim_catch_them_all",
        executable="turtle_controller_node",
        parameters=[
            {"catch_order": "closest"}
        ],
    )
    launch_description.add_action(turtle_controller)

    return launch_description
