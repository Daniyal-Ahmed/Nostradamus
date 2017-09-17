# -*- coding: utf-8 -*-
"""
Created on Sat Sep 16 16:31:54 2017

@author: Goosefield
"""

# This is currently unused in the project however since this implementation
# greatly helped us understand the Bluemix environment and will be 
# incorporated in the project later on, we felt this should be placed in the repo
# as well.

import pandas as pd

# import quandl as qd
import requests

# all names and ID
id_df = pd.read_csv('Sample_Instrument_Universe.csv')

id_df = id_df[id_df['CX Asset Type'] == "Equities"]
id_df = id_df[['ID', 'NAME']]


# Input is the company's name
input_name = "jpmorgan"
date = "2017-09-14"
var = 'THEO/Price'

# values[0] is wrong

input_id = id_df[id_df['NAME'].str.contains(input_name, case=False)]['ID'].values[0]

# ----------------------------



# conn = http.client.HTTPSConnection("fss-analytics.mybluemix.net")

url = "https://fss-analytics.mybluemix.net"
url+= "/api/v1/historical/instrument/"+ input_id + "?date="+date+"&analytics="+var+"/"

headers = {
    'accept': "application/json",
    'content-type': "application/json",
    'x-ibm-access-token': "8cd4a23bd75b483797ab4c37ca63a270ba387b4844996e10f45da93f29a17d497a4221be94cb054def15c7c4d89454eff3c8127d7d7221d310d375ec959c3c19024914c2d3f64719f729996217674ba2f57eb9ebd88c49fa7a1d3fbad16e820a0260fa9a060add26fe958cf647878528f186408cd9d7063f046fb4f9652fbefc"
    }




r = requests.get(url, headers=headers)

a = r.json()[0]

b = a['values'][0][var]

print(b)




    
