import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;
import java.io.IOException;
import java.util.ArrayList;

public class ParsingClass //в этом классе мы делаем парсинг файлов,т.е выбираем файлы img
    //и кладем их в массив
{
    String html;
    private ArrayList<String> mas = new ArrayList<String>();
   // private ArrayList<String> masfortegi = new ArrayList<String>();
    public ParsingClass(String HTML) {
        int i = 0;
        this.html = HTML;
        Document doc = null;
        try {
            doc = Jsoup.connect(html).get();
        } catch (IOException e) {
            e.printStackTrace();
        }
        Elements elements = doc.select("img");
        for (i = 0; i < elements.size(); i++)
        {
        //    masfortegi.add(elements.get(i).attr("alt"));
       //     System.out.println(masfortegi.get(i));
            mas.add(elements.get(i).attr("src"));
            {System.out.println(elements.attr("src"));}
        }
    }


    public class Tegi
    {

    }

    public ArrayList<String> getMas() {
        return mas;
    }

    public void setMas(ArrayList<String> mas) {
        this.mas = mas;
    }
  //  public ArrayList<String> getMasfortegi()
  //  {
  //      return masfortegi;
  //  }

   // public  void setMasfortegi (ArrayList<String> masfortegi)
   // {
   //     this.masfortegi = masfortegi;
   // }
}
