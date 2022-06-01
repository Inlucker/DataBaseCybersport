from faker import Faker
from random import randint
from random import choice


def generateStudios(records_number, countries_n, owners):
    faker = Faker()
    f = open('Studios.csv', 'w')
    for i in range(records_number):
        country_id = randint(1, countries_n)
        # owner_id = randint(1, records_number)
        owner_id = choice(owners)
        line = "{0}|{1}|{2}\n".format(country_id,
                                      owner_id,
                                      faker.company())
        f.write(line)
    f.close()
    print("Finished generating Studios")

# generateStudios(1000, 227)
