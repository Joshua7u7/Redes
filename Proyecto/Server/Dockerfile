FROM node:lts-alpine as build-stage
WORKDIR /app
COPY . /app
RUN npm install
RUN npm i -g typescript
RUN npm run build

FROM node:lts-alpine

LABEL APP_NAME = "Load microservice"
LABEL VERSION = "0.0.1"

ENV FILES_PATH "./dist/public/upload"
ENV PORT "3000"

WORKDIR /load_microservice
COPY --from=build-stage /app/dist /load_microservice/dist
COPY --from=build-stage /app/node_modules /load_microservice/node_modules
EXPOSE 3032
RUN ls
CMD  node ./dist/server.js

