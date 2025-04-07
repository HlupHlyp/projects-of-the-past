from werkzeug.security import generate_password_hash, check_password_hash
import json


class User():

    def __init__(self, name, password_hash):
        self.password_hash = password_hash
        self.name = name
        self.date_time = 0
        self.last_ip = 0
        self.activity = False

    def compare(self, name):
        if (self.name == name):
            return True
        return False

    def enter(self, password):
        return check_password_hash(self.password_hash, password)


class Users_data(User):
    users = []

    def find_user(self, name):
        for i in self.users:
            if (i.compare(name) == True):
                return True
        return False

    def enter(self, name, password):
        for i in self.users:
            if (i.compare(name) == True and check_password_hash(i.password_hash, password) == True):
                return True
        return False

    def add(self, name, password):
        if (self.find_user(name) == True):
            return False
        self.users.append(User(name, generate_password_hash(password)))
        return True

    def save(self, file):
        dicts_list = list()
        for x in self.users:
            result = x.__dict__
            result["className"] = x.__class__.__name__
            dicts_list.append(result)
        with open(file, "w") as data:
            json.dump(dicts_list, data)

    def load(self, file):
        with open(file, "r") as data:
            json_data = json.load(data)
        for x in json_data:
            if (x['className'] == 'User'):
                self.users.append(User(x['name'], x['password_hash']))

    def __init__(self):
        pass

    def show(self):
        for x in self.users:
            print(x.name, x.password_hash, x.activity, x.last_ip)

    def set_last_ip(self, name, ip):
        for i in range(0, len(self.users)):
            if (self.users[i].name == name):
                self.users[i].last_ip = ip
                self.users[i].activity = True
            if (self.users[i].last_ip == ip and self.users[i].name != name):
                self.users[i].activity = False

    def set_non_active(self, ip):
        for i in range(0, len(self.users)):
            if (self.users[i].last_ip == ip):
                self.users[i].activity = False

    def active_ip_finding(self, ip):
        for i in range(0, len(self.users)):
            if (self.users[i].last_ip == ip and self.users[i].activity == True):
                return self.users[i].name
        return False
