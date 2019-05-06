import java.util.ArrayList;
import java.util.List;
/**
 * Décrivez votre classe Doc ici.
 *
 * @author (votre nom)
 * @version (un numéro de version ou une date)
 */
public class Doc
{
    // variables d'instance - remplacez l'exemple qui suit par le vôtre
    private String titre;
    private String nom;
    private int annee;
    private List<Doc> reference;

    /**
     * Constructeur d'objets de classe Doc
     */
    public Doc(String titre, String nom, int annee)
    {
        // initialisation des variables d'instance
        this.titre = titre;
        this.nom = nom;
        this.annee = annee;
        this.reference = new ArrayList<Doc>();
    }
    
    public void ajouter(Doc d)
    {
        this.reference.add(d);
    }
    
    public String toString()
    {
        String s = this.titre + " " + this.nom;
        for (Doc d : reference) {
            s = s + " " + d.titre + " " + d.nom;
        }
        return s;
    }
    
    
    public String getTitle()
    {
        return this.titre;
    }
    
    public String getName()
    {
        return this.nom;
    }
    
    public List<Doc> getListe()
    {
        return this.reference;
    }
    
    public boolean cite(Doc cited)
    {
        for(Doc documents : this.reference)
        {
            if(documents == cited)
            {
                return true;
            }
        }
        return false;
    }
}
