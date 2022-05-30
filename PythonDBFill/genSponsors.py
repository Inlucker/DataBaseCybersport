from faker import Faker
from random import randint


def generateSponsors(records_number, countries_n):
    faker = Faker()
    f = open('Sponsors.csv', 'w')
    for i in range(records_number):
        country_id = randint(1, countries_n)
        line = "{0}|{1}\n".format(country_id,
                                      faker.company())
        f.write(line)
    f.close()
    print("Finished generating Sponsors")

# generateSponsors(1000, 227)
