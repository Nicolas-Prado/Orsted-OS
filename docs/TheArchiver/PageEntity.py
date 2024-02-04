import os

class PageEntity:
    url = None
    folderName = None
    
    def __init__(self, url, folderName):
        self.url = url
        self.folderName = folderName

        os.mkdir(os.path.dirname(folderName))
        #os.makedirs(os.path.dirname(folderName), exist_ok=True)

    def extractPage(folderName, pageEndPoint): 
        