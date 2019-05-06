import java.util.ArrayList;
import java.util.List;
/**
 * Décrivez votre classe Biblio ici.
 *
 * @author (votre nom)
 * @version (un numéro de version ou une date)
 */
public class Biblio
{
    // variables d'instance - remplacez l'exemple qui suit par le vôtre
    private List<Doc> ensemble;

    /**
     * Constructeur d'objets de classe Biblio
     */
    public Biblio()
    {
        // initialisation des variables d'instance
        ensemble = new ArrayList<Doc>();
    }

    public void ajouter(Doc d)
    {
        this.ensemble.add(d);
    }
    
    public String toString()
    {
        String s = "";
        for (Doc d : ensemble) {
            s = s + " " + d.getTitle() + " " + d.getName();
        }
        return s;
    }
    
    public String toString(List<Doc> citants)
    {
        String s = "";
        for (Doc d : citants) {
            s = s + " " + d.getTitle() + " " + d.getName();
        }
        return s;
    }
    
    public Doc rechercheNom(Doc d)
    {
        for (Doc i : this.ensemble) {
            if (i.getName() == d.getName())
            {
                return d;
            }
        }
        return null;
    }
    
    public List<Doc> rechercheDocumentsCitant(Doc cited) {
        List<Doc> citants = new ArrayList<Doc>();
        
        for (Doc document : this.ensemble) {
            if (document.cite(cited)) {
                citants.add(document);
            }
        }
        return citants;
    }
}
