package servletPackage;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import model.Automobile;
import adapter.BuildAuto;

public class CarChoiceServlet extends HttpServlet {

    private BuildAuto buildAuto = null;

    @Override
    public void init() throws ServletException {
        // Servlet initialization code here
        super.init();
        buildAuto = new BuildAuto();
    }

    @Override
    protected void doGet(HttpServletRequest request,
            HttpServletResponse response) throws ServletException, IOException {
        // Set response content type
        response.setContentType("text/html");

        PrintWriter out = response.getWriter();

        String model = request.getParameter("model");
        Automobile automobile = buildAuto.getAuto(model);

        out.println("<head><style>");
        out.println("table, th, td { border: 1px solid black; }");
        out.println("</style></head>");
        out.println("<form action=\"/CIS_35B_-_Lab06/totalcost\">");
        out.println("<table>");
        out.println("<tr>");
        out.println("<th>Make/Model</th>");
        out.println("<td>");
        out.println("<select name=\"model\">");
        out.println("<option value=\"" + model + "\">" + model + "</option>");
        out.println("</select");
        out.println("</td>");
        out.println("</tr>");

        int numOpsets = automobile.getNumOpsets();
        for (int i = 0; i < numOpsets; ++i) {
            String opsetName = automobile.getOpsetName(i);
            ArrayList<String> optNames = automobile.getOpsetOptNames(i);

            out.println("<tr>");
            out.println("<th>" + opsetName + "</th>");
            out.println("<td>");
            out.println("<select name=\"" + opsetName.toLowerCase() + "\">>");
            for (int j = 0; j < optNames.size(); ++j) {
                out.println("<option value=\"" + optNames.get(j) + "\">"
                        + optNames.get(j) + "</option>");
            }
            out.println("</select");
            out.println("</td>");
            out.println("</tr>");
        }

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