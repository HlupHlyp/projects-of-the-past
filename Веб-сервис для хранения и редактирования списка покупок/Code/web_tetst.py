from flask import *
from werkzeug.security import generate_password_hash, check_password_hash
import json
from Class_User import *
from Class_Card import *

app = Flask(__name__)

Users = Users_data()

Cards = Cards_data()

Users.load('users.json')

Cards.load('cards.json')

Users.show()


@app.route('/exit')
def exit():
    Users.set_non_active(request.remote_addr)
    return entrance()


@app.route('/')
def entrance():
    return render_template('Entrance.html')


@app.route('/sign_up/', methods=['post', 'get'])
def sign_up():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        conf_pas = request.form.get('conf_pas')
        if (Users.find_user(username) == True):
            return render_template('Sign_up_form.html', message='There is user with such name')
        elif (password != conf_pas):
            return render_template('Sign_up_form.html', message='Passwords don\'t match')
        Users.add(username, password)
        Users.set_last_ip(username, request.remote_addr)
        Cards.add_card(username, items=[])
        Users.save('users.json')
        return render_template('Shopping_cart.html', message=username + '\'s card')
    return render_template('Sign_up_form.html', message='Registration')


@app.route('/log_in/', methods=['post', 'get'])
def log_in():
    if request.method == 'POST':
        username = request.form.get('username')  # запрос к данным формы
        password = request.form.get('password')
        if (Users.find_user(username) == True):
            if (Users.enter(username, password) == False):
                return render_template('Log_in_form.html', message='Wrong password')
            else:
                Users.set_last_ip(username, request.remote_addr)
                Users.save('users.json')
                return render_template('Shopping_cart.html', message=username + '\'s card')
        else:
            return render_template('Log_in_form.html', message='There is no user with such name')
    return render_template('Log_in_form.html', message='Authorization')


@app.route('/add_item', methods=['post', 'get'])
def add_item():
    item = ''
    owner = Users.active_ip_finding(request.remote_addr)
    if request.method == 'POST':
        content = request.json
        item = content['item']
    if (owner == False):
        return entrance()
    else:
        Cards.add_to_user_card(owner, item)
        Cards.save('cards.json')
        return make_response("", 200)


@app.route('/del_item', methods=['post', 'get'])
def del_item():
    item = ''
    owner = Users.active_ip_finding(request.remote_addr)
    if request.method == 'POST':
        content = request.json
        item = content['item']
    if (owner == False):
        return entrance()
    else:
        Cards.del_from_user_card(owner, item)
        Cards.save('cards.json')
        return make_response("", 200)


@app.route('/renew', methods=['post', 'get'])
def renew():
    owner = Users.active_ip_finding(request.remote_addr)
    if (owner == False):
        return entrance()
    else:
        return make_response(Cards.no_user_items(owner), 200)


@app.route('/catalog', methods=['post', 'get'])
def catalog():
    if (Users.active_ip_finding(request.remote_addr) == False):
        return entrance()
    return render_template('Catalog.html', message='Authorization')


@app.route('/shopping_cart')
def Shopping_cart():
    owner = Users.active_ip_finding(request.remote_addr)
    if (owner == False):
        return entrance()
    return render_template('Shopping_cart.html', message=owner + '\'s card')


if __name__ == "__main__":
    app.run(host='0.0.0.0', port=4567)
