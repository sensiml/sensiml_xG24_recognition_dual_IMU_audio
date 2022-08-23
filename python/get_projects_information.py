from sensiml import Client

client = Client()
client.project = "Smart_Lock_IMU"

print("############" * 3)
print("Projet", client.project.name)
print("############" * 3)
print("Capture Configurations")
print(client.list_capture_configurations())
print("Knowledge Pack")
print(client.project.list_knowledgepacks())

client.project = "Smart_Lock_Audio"
print("############" * 3)
print("Project: Smart_Lock_Audio")
print("############" * 3)
print("Capture Configurations")
print(client.list_capture_configurations())
print("Knowledge Pack")
print(client.project.list_knowledgepacks())
