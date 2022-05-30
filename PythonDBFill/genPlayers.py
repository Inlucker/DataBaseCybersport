from faker import Faker
from random import randint
from random import choice
import datetime

role = ["SafeLaner", "MidLaner", "OffLaner", "SoftSupport", "HardSupport"]


def generatePlayers(records_number, countries_n):
    players = dict()
    faker = Faker()
    f = open('Players.csv', 'w')
    for i in range(records_number):
        now = datetime.datetime.now()
        min_year = now.year - 30
        max_year = now.year - 9
        age = randint(min_year, max_year)
        rating = randint(1, 8000)
        team_id = randint(1, records_number)
        country_id = randint(1, countries_n)
        line = "{0}|{1}|{2}|{3}|{4}|{5}|{6}|{7}\n".format(team_id,
                                                          country_id,
                                                          faker.user_name(),
                                                          faker.first_name_male(),
                                                          faker.last_name_male(),
                                                          age,
                                                          choice(role),
                                                          rating)
        players[i + 1] = rating
        f.write(line)
    f.close()
    print("Finished generating Players")
    return players

# generatePlayers(1000, 227)
