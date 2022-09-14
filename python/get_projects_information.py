import json
from sensiml import Client
from sensiml.datamanager.knowledgepack import KnowledgePack

client = Client()

client.project = "Smart_Lock_Audio"

print("Uploading PreTrained Audio Model to your Project")
kp_audio = KnowledgePack(client._connection, client.project.uuid)
kp_audio.initialize_from_dict(json.load(open("audio_model.json", "r")))
kp_audio._name = "AudioModel"
kp_audio.create()

print("############" * 3)
print("Projet", client.project.name)
print("############" * 3)
print("Capture Configurations")
print(client.list_capture_configurations())
print("Knowledge Pack")
print(client.project.list_knowledgepacks())

client.project = "Smart_Lock_IMU"
print("Uploading PreTrained IMU Model to your Project")
kp_imu = KnowledgePack(client._connection, client.project.uuid)
kp_imu.initialize_from_dict(json.load(open("imu_model.json", "r")))
kp_imu._name = "IMUModel"
kp_imu.create()


print("############" * 3)
print("Projet", client.project.name)
print("############" * 3)
print("Capture Configurations")
print(client.list_capture_configurations())
print("Knowledge Pack")
print(client.project.list_knowledgepacks())
