import os, time, math
import pybullet as p
import pybullet_data

here = os.path.dirname(os.path.abspath(__file__))

p.connect(p.GUI)
p.setAdditionalSearchPath(pybullet_data.getDataPath())
p.loadURDF("plane.urdf")
p.resetDebugVisualizerCamera(cameraDistance=0.9, cameraYaw=50, cameraPitch=-20,
                             cameraTargetPosition=[0, 0.15, 0.1])

urdf_path = os.path.join(here, "arm5.urdf")
print("Đang nạp URDF:", urdf_path, "| tồn tại:", os.path.exists(urdf_path))
robot = p.loadURDF(urdf_path, useFixedBase=True)


idx = {p.getJointInfo(robot, j)[1].decode(): j for j in range(p.getNumJoints(robot))}
print(idx)

# 4 khớp quay: thanh trượt theo độ
names = ["j1_base", "j2_shoulder", "j3_elbow", "j4_wrist"]
sliders = {n: p.addUserDebugParameter(n, -180, 180, 0) for n in names}
# kẹp: một thanh trượt = góc servo kẹp (độ). Hai bánh răng ăn khớp nên hai hàm xoay ngược chiều, cùng độ lớn
s_grip = p.addUserDebugParameter("j5_gripper (độ, + = mở)", -20, 40, 0)


def set_pose(angles_deg, grip_deg):
    """angles_deg: dict tên khớp -> độ. grip_deg: góc servo kẹp (độ)."""
    for n, a in angles_deg.items():
        p.resetJointState(robot, idx[n], math.radians(a))
    g = math.radians(grip_deg)
    p.resetJointState(robot, idx["j5_jaw_up"], g)
    p.resetJointState(robot, idx["j5_jaw_low"], -g)


while p.isConnected():
    set_pose({n: p.readUserDebugParameter(s) for n, s in sliders.items()},
             p.readUserDebugParameter(s_grip))
    p.stepSimulation()
    time.sleep(1 / 240)
