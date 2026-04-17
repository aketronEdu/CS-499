from pymongo import MongoClient
from bson.objectid import ObjectId

class AnimalShelter(object):

    def __init__(self, username='aacuser', password='SNHU1234', role='user'):
        # Connection variables
        USER = username
        PASS = password
        HOST = 'nv-desktop-services.apporto.com'
        PORT = 30847
        DB = 'AAC'
        COL = 'animals'

        # Initialize Connection
        self.client = MongoClient("mongodb://localhost:27017")
        self.database = self.client["AAC"]
        self.collection = self.database["animals"]
        self.role = role

    def is_admin(self):
        return self.role == "admin"


#Create
    def create(self, data):
        if not self.is_admin():
            raise Exception("Unauthorized: Admins only")

        if data is not None:
            try:
                self.collection.insert_one(data)
                return True
            except Exception as e:
                print(f"Insert failed : {e}")
                return False
        else:
            raise Exception("Nothing to save, because data parameter is empty")


#Read
    def read(self, query):
        if query is not None:
            try:
                cursor = self.collection.find(query)
                result = list(cursor)
                return result
            except Exception as e:
                print(f"Read failed : {e}")
                return []
        else:
            raise Exception("Query parameter is empty")


#Update
    def update(self, filter_dict, update_dict, many=False):
        if not self.is_admin():
            raise Exception("Unauthorized: Admins only")

        if many:
            result = self.collection.update_many(filter_dict, update_dict)
        else:
            result = self.collection.update_one(filter_dict, update_dict)

        return result.modified_count


#Delete
    def delete(self, filter_dict, many=False):
        if not self.is_admin():
            raise Exception("Unauthorized: Admins only")

        if many:
            result = self.collection.delete_many(filter_dict)
        else:
            result = self.collection.delete_one(filter_dict)

        return result.deleted_count