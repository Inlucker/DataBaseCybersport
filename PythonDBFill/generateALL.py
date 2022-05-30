from genUserRoles import generateUserRoles
from genUsers import generateUsers
from genCountries import generateCountries
from genSponsors import generateSponsors
from genTeams import generateTeams
from genPlayers import generatePlayers
from genStudios import generateStudios
from genCommentators import generateCommentators
from genTournaments import generateTournaments
from genMatches import generateMatches
from genTournamentTeams import generateTournamentTeams

RECORDS_N = 1000

generateUserRoles()
generateUsers(RECORDS_N)
COUNTRIES_N = generateCountries()
generateSponsors(RECORDS_N, COUNTRIES_N)
generateTeams(RECORDS_N, COUNTRIES_N)
generatePlayers(RECORDS_N, COUNTRIES_N)
generateStudios(RECORDS_N, COUNTRIES_N)
generateCommentators(RECORDS_N, COUNTRIES_N)
generateTournaments(RECORDS_N, COUNTRIES_N)
generateMatches(RECORDS_N)
generateTournamentTeams(RECORDS_N)

print("Finished generating ALL")