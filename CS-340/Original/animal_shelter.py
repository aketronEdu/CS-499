from pymongo import MongoClient
from bson.objectid import ObjectId

class AnimalShelter(object):
            def __init__(self, username='aacuser', password='SNHU1234'):
                # Connection variables
                USER = username
                PASS = password
                HOST = 'nv-desktop-services.apporto.com'
                PORT = 30847
                DB = 'AAC'
                COL = 'animals'
                # Initialize Connection
                #
                self.client = MongoClient("mongodb://localhost:27017")
                self.database = self.client["AAC"]
                self.collection = self.database["animals"]

# Complete this create method to implement the C in CRUD.
            def create(self, data):
                if data is not None:
                    try:
                        self.database.animals.insert_one(data) # data should be dictionary 
                        return True
                    except Exception as e:
                        print(f"Insert failed : {e}")
                        return False
                else:
                    raise Exception("Nothing to save, because data parameter is empty")

# Create method to implement the R in CRUD.
            def read(self, query):
                if query is not None:
                    try:
                        cursor = self.database.animals.find(query)
                        result = list(cursor)
                        return result
                    except Exception as e:
                        print(f"Read failed : {e}")
                        return[]
                else:
                    raise Exception("Query parameter is empty")
                    
# Update method
            def update(self, filter_dict, update_dict, many=False):
                if many:
                    result = self.collection.update_many(filter_dict, update_dict)
                else:
                    result = self.collection.update_one(filter_dict, update_dict)
                return result.modified_count
# Delete method
            def delete(self, filter_dict, many=False):
                if many:
                    result = self.collection.delete_many(filter_dict)
                else:
                    result = self.collection.delete_one(filter_dict)
                return result.deleted_count
