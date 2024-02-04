import requests
import os

fileText = requests.get('http://www.brokenthorn.com/Resources/OSDev0.html')

os.makedirs(os.path.dirname('test/test.html'), exist_ok=True)

file = open('test/test.html', 'w')
file.write(fileText.content.decode())
file.close()