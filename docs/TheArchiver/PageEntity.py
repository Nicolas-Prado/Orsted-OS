import os
import requests
from bs4 import BeautifulSoup

class PageEntity:
    url = None
    folderName = None
    
    def __init__(self, url, folderName):
        self.url = url
        self.folderName = folderName
        self.folderPath = '../' + folderName

        os.makedirs(os.path.dirname(self.folderPath), exist_ok=True)

    def extractPage(self, subfolderName, resource): 
        subfolderPath = self.folderPath + '/' + subfolderName
        os.makedirs(os.path.dirname(subfolderPath), exist_ok=True)
        #os.mkdir(os.path.dirname(subfolderPath))

        htmlResponse = requests.get(self.url + resource)

        try:
            htmlText = htmlResponse.content.decode('utf-8')
        except:
             htmlText = htmlResponse.content.decode('ISO-8859-1')
        os.makedirs(os.path.dirname(subfolderPath + '/index.html'), exist_ok=True)
        file = open(subfolderPath + '/index.html', 'w', encoding='utf-8')
        file.write(htmlText)
        file.close()

        soup = BeautifulSoup(htmlResponse.content, 'html.parser')
        imageDependencies = self.__getPageDependencies('img', soup)
        cssDependencies = self.__getPageDependencies('link', soup)

        self.__persistDependencies(subfolderPath, imageDependencies + cssDependencies)

    def __getPageDependencies(self, tag, soup):
        if tag == 'img':
            dependeciesResourceUrl = [img['src'] for img in soup.find_all('img', src=True)]
        elif tag == 'link':
            dependeciesResourceUrl = [link['href'] for link in soup.find_all('link', href=True)]
        else:
            raise Exception('Dependence not mapped')
        
        dependeciesResourceUrl = [url.replace(self.url, '') for url in dependeciesResourceUrl]
        dependeciesResourceUrl = [url for url in dependeciesResourceUrl if 'http:' not in url]
        
        return [self.__getDependence(dependenceResourceUrl) for dependenceResourceUrl in dependeciesResourceUrl]
    
    def __getDependence(self, url):
        dependenceResponse = requests.get(self.url + url)

        return {"dependencePath": url, "dependenceResource": dependenceResponse}
    
    def __persistDependencies(self, subfolderPath, dependecies):
        for dependence in dependecies:
            os.makedirs(os.path.dirname(subfolderPath + '/' + dependence['dependencePath']), exist_ok=True)
            with open(subfolderPath + '/' + dependence['dependencePath'], 'wb') as file:
                file.write(dependence['dependenceResource'].content)