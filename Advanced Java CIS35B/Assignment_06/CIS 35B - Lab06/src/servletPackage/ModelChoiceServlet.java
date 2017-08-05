package servletPackage;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Set;

import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import adapter.BuildAuto;

public class ModelChoiceServlet extends HttpServlet {

    private BuildAuto buildAuto = null;

    @Override
    public void init() throws ServletException {
        // Servlet initialization code here
        super.init();
        buildAuto = new BuildAuto();

        ServletContext context = getServletContext();
        
        // Build first Automobile.
        String fileName = context.getRealPath("WEB-INF\\FordZTW.txt");
        buildAuto.buildAuto(fileName);
        
        // Build second Automobile.
        fileName = context.getRealPath("WEB-INF\\HondaAccord.txt");
        buildAuto.buildAuto(fileName);
    }

    @Override
    protected void doGet(HttpServletRequest request,
            HttpServletResponse response) throws ServletException, IOException {
        // Set response content type
        response.setContentType("text/html");

        // Actual logic goes here.
        PrintWriter out = response.getWriter();

        Set<String> modelNamesSet = buildAuto.getModelNames();
        String modelNames[] = modelNamesSet.toArray(new String[modelNamesSet.size()]);

        out.println("<head><style>");
        out.println("table, th, td { border: 1px solid black; }");
        out.println("</style></head>");
        out.println("<form action=\"/CIS_35B_-_Lab06/carchoice\">");
        out.println("<table>");
        out.println("<tr>");
        out.println("<th>Make/Model</th>");
        out.println("<td>");
        out.println("<select name=\"model\">");
        for (int i = 0; i < modelNames.length; ++i) {
            out.println(
                    "<option value=\"" + modelNames[i] + "\">" + modelNames[i] + "</option>");
        }
        out.println("</select");
        out.println("</td>");
        out.println("</tr>");
        out.println("</table>");
        out.println("<input type=\"submit\" value=\"Done\">");
        out.println("</form>");
    }

    @Override
    public void destroy() {
        // resource release
        super.destroy();
    }
}