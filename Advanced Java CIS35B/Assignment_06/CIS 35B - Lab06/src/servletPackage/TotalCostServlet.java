package servletPackage;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import model.Automobile;
import adapter.BuildAuto;

public class TotalCostServlet extends HttpServlet {

    private BuildAuto buildAuto = null;

    @Override
    public void init() throws ServletException {
        // Servlet initialization code here
        super.init();
        buildAuto = new BuildAuto();
        System.out.println("TotalCostServlet constructor.");
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

        out.println("<table>");
        out.println("<tr>");
        out.println("<td>Focus Wagon ZTW</td>");
        out.println("<td>base price</td>");
        out.println("<td>" + automobile.getBasePrice() + "</td>");
        out.println("</tr>");

        int numOpsets = automobile.getNumOpsets();
        for (int i = 0; i < numOpsets; ++i) {
            String opsetName = automobile.getOpsetName(i);
            String optName = request.getParameter(opsetName.toLowerCase());
            automobile.setOptionChoice(opsetName, optName);

            out.println("<tr>");
            out.println("<td>" + opsetName + "</td>");
            out.println("<td>" + optName + "</td>");
            out.println("<td>" + automobile.getOptionPrice(opsetName, optName)
                    + "</td>");
            out.println("</td>");
            out.println("</tr>");
        }
        out.println("<tr>");
        out.println("<th>Total Cost</td>");
        out.println("<td></td>");
        out.println("<td>" + automobile.getTotalPrice() + "</td>");
        out.println("</tr>");
        out.println("</table>");
    }

    @Override
    public void destroy() {
        // resource release
        super.destroy();
    }
}