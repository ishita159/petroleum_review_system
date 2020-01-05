import requests

# Step 1) Find the public IP of the user. This is easier said that done, look into the library Netifaces if you're
# interested in getting the public IP locally.
# The GeoIP API I'm going to use here is 'https://geojs.io/' but any service offering similar JSON data will work.

ip_request = requests.get('https://get.geojs.io/v1/ip.json')
my_ip = ip_request.json()['ip']  # ip_request.json() => {ip: 'XXX.XXX.XX.X'}
# Prints The IP string, ex: 198.975.33.4

# Step 2) Look up the GeoIP information from a database for the user's ip

geo_request_url = 'https://get.geojs.io/v1/ip/geo/' + my_ip + '.json'
geo_request = requests.get(geo_request_url)
geo_data = geo_request.json()
print(geo_data['latitude'])
print(geo_data['longitude'])
#blah blah blah
