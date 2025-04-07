import json
catalog = ['carrot', 'banana', 'orange', 'apple', 'blueberry']


class Card():

    def is_item(self, item):
        for x in self.items:
            if (x == item):
                return True
        return False

    def __init__(self, owner, items=[]):
        self.owner = owner
        self.items = items


class Cards_data(Card):

    cards = []

    def find_user_card(self, owner):
        for i in range(0, len(self.cards)):
            if (self.cards[i].owner == owner):
                return i
        return -1

    def add_card(self, owner, items=[]):
        if (self.find_user_card(owner) == -1):
            self.cards.append(Card(owner, items))

    def add_to_user_card(self, owner, item):
        n = self.find_user_card(owner)
        if (n == -1):
            print('add-')
            self.add_card(owner)
        n1 = self.find_user_card(owner)
        if not (item in self.cards[n].items):
            self.cards[n].items.append(item)

    def del_from_user_card(self, owner, item):
        n = self.find_user_card(owner)
        if (n == -1):
            print('del-' + owner)
            self.add_card(owner)
        n1 = self.find_user_card(owner)
        if (item in self.cards[n].items):
            self.cards[n].items.remove(item)

    def save(self, file):
        dicts_list = list()
        for x in self.cards:
            result = x.__dict__
            result["className"] = x.__class__.__name__
            dicts_list.append(result)
        with open(file, "w") as data:
            json.dump(dicts_list, data)

    def load(self, file):
        with open(file, "r") as data:
            json_data = json.load(data)
        for x in json_data:
            if (x['className'] == 'Card'):
                self.cards.append(Card(x['owner'], x['items']))

    def no_user_items(self, owner):
        n = self.find_user_card(owner)
        res = ''
        if (n != -1):
            for i in catalog:
                if not (i in self.cards[n].items):
                    res += i + ','
        return res

    def user_items(self, owner):
        n = self.find_user_card(owner)
        res = ''
        if (n != -1):
            for i in self.cards[n].items:
                res += i +', '
            if len(self.cards[n].items) != 0:
                res = res[:-2]
        return res

    def __init__(self):
        pass

    def show(self):
        for x in self.cards:
            print(x.owner, x.items)
