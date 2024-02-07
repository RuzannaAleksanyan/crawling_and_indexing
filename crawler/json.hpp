{
  "project": {
    "xmlns": "http://maven.apache.org/POM/4.0.0",
    "xmlns:xsi": "http://www.w3.org/2001/XMLSchema-instance",
    "xsi:schemaLocation": "http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd",
    "modelVersion": "4.0.0",
    "groupId": "org.example",
    "artifactId": "Crawler",
    "version": "1.0-SNAPSHOT",
    "properties": {
      "maven.compiler.source": "11",
      "maven.compiler.target": "11",
      "project.build.sourceEncoding": "UTF-8"
    },
    "dependencies": [
      {
        "groupId": "org.jsoup",
        "artifactId": "jsoup",
        "version": "1.17.2"
      },
      {
        "groupId": "org.apache.httpcomponents",
        "artifactId": "httpclient",
        "version": "4.5.13"
      },
      {
        "groupId": "com.fasterxml.jackson.core",
        "artifactId": "jackson-databind",
        "version": "2.14.0-rc1"
      }
    ]
  }
}
