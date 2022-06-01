from faker import Faker
from random import randint
import datetime


def generateCommentators(records_number, countries_n):
    faker = Faker()
    f = open('Commentators.csv', 'w')
    for i in range(records_number*5):
        studio_id = ""
        if (randint(0, 1)):
            studio_id = randint(1, records_number)
        country_id = randint(1, countries_n)
        now = datetime.datetime.now()
        min_year = now.year - 30
        max_year = now.year - 9
        age = randint(min_year, max_year)
        popularity = randint(1, 8000)
        line = "{0}|{1}|{2}|{3}|{4}|{5}|{6}\n".format(studio_id,
                                                      country_id,
                                                      faker.user_name(),
                                                      faker.first_name_male(),
                                                      faker.last_name_male(),
                                                      age,
                                                      popularity)
        f.write(line)
    f.close()
    print("Finished generating Commentators")

# generateCommentators(1000, 227)
