from faker import Faker
from random import randint

def generateCountries(records_number):
    faker = Faker()
    countries = []

    for i in range(records_number):
        new_country = faker.country()
        while (new_country in countries):
            new_country = faker.country()
        countries.append(new_country)
    countries.sort()
    print(countries)

    print("Finished generating countries")

# generateCountries(100)
