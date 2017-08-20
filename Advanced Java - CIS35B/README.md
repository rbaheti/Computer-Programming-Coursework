Car Configuration Web Application in Java  

This web application was built in steps and spanned 6 assignments, each building on top of the previous assignment. The complete web app built in [Assignment 6](Assignment6) allows users to choose a car model, configure the model and get its final price based on the options chosen (e.g. color, transmission etc.). I used Java Servlets and Apache Tomcat for serving the web pages of the web app.  The configuration available on a car model is read from text files under the [WEB-INF](Assignment6/WebContent/WEB-INF/) directory.
<br>
Following are the screenshots of the simple Web UI of the app.  
1. Car Model Choice Page ([Link to Servlet Code](Assignment6/src/servletPackage/ModelChoiceServlet.java))  
![](https://user-images.githubusercontent.com/9449212/29497873-36a822a4-85a5-11e7-9449-05967e11cf90.png)
<br>
2. Car Option Choice Page ([Link to Servlet Code](Assignment6/src/servletPackage/CarChoiceServlet.java))  
![](https://user-images.githubusercontent.com/9449212/29497875-39915ec2-85a5-11e7-8e3a-3c5e4569bee3.png)
<br>
3. Total Cost Page ([Link to Servlet Code](Assignment6/src/servletPackage/TotalCostServlet.java))  
![](https://user-images.githubusercontent.com/9449212/29497876-3afa5778-85a5-11e7-85c4-c52062208429.png)