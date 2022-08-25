from sensiml import Client

# Replace with UUID associated with your model and capture configuration

AUDIO_MODEL_UUID = "9c64139e-d32a-4a26-8521-fb3bcfb46f81"
AUDIO_MODEL_SOURCE_UUID = "6ca413e1-474b-4058-99b7-8ab75a6a2c6a"
IMU_MODEL_UUID = "bab2eb7e-7dfd-428b-8509-72b12b1e6dcb"
IMU_MODEL_SOURCE_UUID = "f66d2842-8e74-48bd-bbc9-8a56c73684a4"


client = Client(server="sensiml", insecure=True)
client.project = "Smart_Lock_IMU"

kb_description = {
    "AUDIO_MODEL": {
        "source": AUDIO_MODEL_SOURCE_UUID,
        "uuid": AUDIO_MODEL_UUID,
    },
    "IMU_MODEL": {
        "source": IMU_MODEL_SOURCE_UUID,
        "uuid": IMU_MODEL_UUID,
    },
}

kp_imu = client.get_knowledgepack(kb_description["IMU_MODEL"]["uuid"])
kp_audio = client.get_knowledgepack(kb_description["AUDIO_MODEL"]["uuid"])

xg24_config = client.platforms.get_platform_by_name(
    "Silicon Labs xG24 Dev Kit"
).get_config()
xg24_config["hardware_accelerator"] = "siliconlabs"
xg24_config["kb_description"] = kb_description

kp_path, status = kp_imu.download_library_v2(config=xg24_config)

print("Downloaded Model to", kp_path)
