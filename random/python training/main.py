import json

class FileNotJsonFormatError(Exception):
	def __init__(self):
		self.message = "Vous ne pouvez mettre que des fichiers .json"

def read_json_file(filename):
	try:
		if not filename.endswith('.json'):
			raise FileNotJsonFormatError
		fichier = open(filename)
		print(json.load(fichier))
		fichier.close()
	except FileNotJsonFormatError as e:
		print(e.message)
	except FileNotFoundError:
		print("Le fichier n'existe pas")

read_json_file(input("Quel est le nom du fichier ?\n"))