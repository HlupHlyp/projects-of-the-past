from Class_Card import *
from Class_User import *
from telebot import *
bot = telebot.TeleBot('6893332938:AAEvs3DyR1-nL2b_Xzxvgf821oA_CAc1T6k')

dictionary = {}

Users = Users_data()

Cards = Cards_data()

Users.load('users.json')

Cards.load('cards.json')


@bot.message_handler(content_types=['text'])
def get_text_messages(message):
    keyboard = types.InlineKeyboardMarkup()  # наша клавиатура
    key_start = types.InlineKeyboardButton(
        text='Получить список', callback_data='list')
    keyboard.add(key_start)
    key_end = types.InlineKeyboardButton(
        text='Ничего', callback_data='nothing')
    keyboard.add(key_end)
    bot.send_message(message.from_user.id, text="Что вы хотите?",
                     reply_markup=keyboard)


@bot.callback_query_handler(func=lambda call: True)
def callback_worker(call):
    if call.data == "list" or call.data == "re_username":
        bot.send_message(call.message.chat.id, "Введите логин")
        bot.register_next_step_handler(call.message, get_username)
    elif call.data == "end":
        bot.send_message(call.message.chat.id, "Хорошего дня")
    elif call.data == "re_password":
        bot.send_message(call.message.chat.id, "Введите пароль")
        bot.register_next_step_handler(call.message, get_password)


def get_username(message):
    username = message.text
    if (Users.find_user(username) == True):
        bot.send_message(message.from_user.id,
                         "Пользователь найден. Введите пароль.")
        bot.register_next_step_handler(message, get_password)
        id = message.from_user.id
        dictionary[str(id)] = str(username)
    else:
        keyboard = types.InlineKeyboardMarkup()
        keyboard = types.InlineKeyboardMarkup()  # наша клавиатура
        key_restart = types.InlineKeyboardButton(
            text='Ввести логин снова', callback_data='re_username')
        keyboard.add(key_restart)
        key_stop = types.InlineKeyboardButton(
            text='Прервать вход', callback_data='end')
        keyboard.add(key_stop)
        bot.send_message(message.from_user.id, text="Пользователь не найден.",
                         reply_markup=keyboard)

    print(message.text)


def get_password(message):
    password = message.text
    id = message.from_user.id

    if (Users.enter(dictionary.get(str(id)), password) == False):
        keyboard = types.InlineKeyboardMarkup()
        keyboard = types.InlineKeyboardMarkup()  # наша клавиатура
        key_restart = types.InlineKeyboardButton(
            text='Ввести пароль снова', callback_data='re_password')
        keyboard.add(key_restart)
        key_stop = types.InlineKeyboardButton(
            text='Прервать вход', callback_data='end')
        keyboard.add(key_stop)
        bot.send_message(message.from_user.id, text="Пароль неверный.",
                         reply_markup=keyboard)
    else:
        bot.send_message(message.from_user.id, text="Вход осуществлен.")
        bot.send_message(message.from_user.id, text="Ваш список:")
        bot.send_message(message.from_user.id,
                         text=Cards.user_items(dictionary.get(str(id))))


bot.polling(none_stop=True, interval=0)
