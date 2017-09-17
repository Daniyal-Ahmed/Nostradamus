# -*- coding: utf-8 -*-
"""
Created on Sun Sep 17 02:12:04 2017

@author: Goosefield
"""
import aylien_news_api
from aylien_news_api.rest import ApiException

import pandas as pd

import json
from watson_developer_cloud import NaturalLanguageUnderstandingV1
import watson_developer_cloud.natural_language_understanding.features.v1 \
  as Features

natural_language_understanding = NaturalLanguageUnderstandingV1(
  username="3b1e28b6-5a9e-4d7e-aa2e-b8ce6a6e0ae7",
  password="HHhE45ZoWEuC",
  version="2017-02-27")

linkLists = []
scoreList = []

# Configure API key authorization: app_id
aylien_news_api.configuration.api_key['X-AYLIEN-NewsAPI-Application-ID'] = '05e79c14'
# Configure API key authorization: app_key
aylien_news_api.configuration.api_key['X-AYLIEN-NewsAPI-Application-Key'] = '21d2c31fa3055e54186dc48162d23202'

# create an instance of the API class
api_instance = aylien_news_api.DefaultApi()

stock = "WMT"

opts = {
  'title': stock,
  'sort_by': 'social_shares_count.facebook',
  'language': ['en'],
  'published_at_start': 'NOW-20DAYS',
  'published_at_end': 'NOW',
}

api_response = api_instance.list_stories(**opts)
for story in api_response.stories:
  elements = story.links.canonical
  if elements != (None):
    linkLists.append(elements)
    
###############################################################################
    
for linkElement in linkLists:
    
  response = natural_language_understanding.analyze(
    url = linkElement,
    features=[
      Features.Entities(
        emotion=True,
        sentiment=True,
        limit=2
      ),
    ]
  )
  
  list1 = response['entities']
  
  element = list1[0]
  
  score = element['sentiment']
  
  percentage = score['score']
  
  scoreList.append(percentage)
  
scoreSum = sum(scoreList)
scoreLen = len(scoreList)

if scoreLen != 0:
  averageScore = sum(scoreList) / len(scoreList)
else:
  averageScore = 0
  
if averageScore > 0:
  scoreVector = 'Positive'
elif averageScore == 0:
  scoreVector = 'Neutral'
else:
  scoreVector = 'Negative'

# print(averageScore)
print("Ticker: " + stock)

print("Public News Sentiment: " + scoreVector)

prob_df = pd.read_csv(stock+'-prob.csv')

val = prob_df.iloc[prob_df['Value'].argmax()]['Prob']
print("Historical trend forecast: " + val)

maxGF = prob_df.iloc[prob_df['Value'].argmax()]['Value']
maxEV = averageScore

if val == "Increase":
    maxGF = abs(maxGF)
elif maxGF == "Decrease":
    maxGF = maxGF * (-1)
else:
    maxGF = 0
    
balancedGF = maxGF / 2
balancedEV = maxEV * 2

finalMagnitude = (balancedGF + balancedEV) / 2
if finalMagnitude > 0:
    finalVector = "Increase"
elif finalMagnitude < 0:
    finalVector = "Decrease"
else:
    finalVector = 0
    
print("Final: " + finalVector)




















