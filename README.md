# TCP-IP-Chat

В данной программе реализованна логика TCP/ip чата с помощью библиотеки SFML

# Реализованны следующие функции:

##### Сервер:
  - Создания сервера для обмена сообщениями.
  - Выбор желаемого порта.
  - Мониторинг пользователей онлайн.
  - Прием сообщения от клиента и переотправление всем подлюченным

##### Клиент:
 
 - Подключение к сервуру по IP
 - Просмотрт онлайн пользователей (для этого нужно отправить в чат "!")
 - обмен сообщений между клиентами в режиме онлайн

### TO-DO

 - Адаптировать для кросплатфоременного выполнения
 - Makefile
 - Написать отдельную программу для мониторинга онлайна
 - QT GUI

# Команды компиляции
Перед компиляцией проекта требуется установить библиотеку SFML
Для её установки нужно выполнить команду:
```sh
sudo apt-get install libsfml-dev
```

Для компиляции проекта можно использовать следующие команды
```sh
echo компиляция клиентской части
g++ ./client/Client.cpp ./client/Client.h ./client/PacketType.h ./client/client_main.cpp -o sfml-client -lsfml-system -lsfml-network -std=c++14
```
```sh
echo компиляция серверной части
g++ ./server/Server.cpp ./server/Server.h ./server/server_main.cpp -o sfml-server -lsfml-system -lsfml-network -std=c++14
```
```sh
echo компиляция комбинорлванного приложения
g++ ./client/Client.cpp ./client/Client.h ./client/PacketType.h ./main.cpp ./server/Server.cpp ./server/Server.h -o sfml-project -lsfml-system -lsfml-network -std=c++14
```


### Скрины работы
Окно сервера
![](https://pp.userapi.com/c841024/v841024934/8c/n9uYiR3wgbc.jpg)
Окна клиентов
![](https://pp.userapi.com/c841024/v841024934/83/qcmPijQXMoo.jpg)
![](https://pp.userapi.com/c841024/v841024934/95/sJ1qUdssqwg.jpg)



© Вячеслав Ефименков
evslav@bk.ru
+7(910)398-37-54
