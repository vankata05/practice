FROM node:17-alpine

WORKDIR /app

#needed packages for project
COPY package.json .

#installs the needed
RUN npm install

#copy the directory where the file is located and paste it in the same directory + /app
COPY . .

#expose/open port 3000
EXPOSE 3000

#run the app inside the container
CMD ["npm", "start"]
