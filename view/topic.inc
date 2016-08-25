<?php
require_once('parts/header.inc');
?>
<?php /*
// on se connecte à MySQL 
$db = mysql_connect('172.26.10.110', 'admin', ''); 

// on sélectionne la base 
mysql_select_db('forum',$db); 

// on crée la requête SQL 
$sql = 'SELECT (select titre from categorie where topic.id_categorie = categorie.id_categorie)as id_categorie,titre,(select prenom from user where topic.id_user = user.id_user) as id_user FROM topic'; 

// on envoie la requête 
$req = mysql_query($sql) or die('Erreur SQL !<br>'.$sql.'<br>'.mysql_error()); 

// on fait une boucle qui va faire un tour pour chaque enregistrement 
while($data = mysql_fetch_assoc($req)) 
    { 
    // on affiche les informations de l'enregistrement en cours 
    echo '<h4><b>'.$data['id_categorie'].' / '.$data['titre'].' créé(e) par : '.$data['id_user'].'</b><h4/>'; 
    
    } 

// on ferme la connexion à mysql 
mysql_close(); */
?>

<!--Bouton permettant le hide/show du formulaire-->
<div class="navbar navbar-default navbar-static">
    <div class="container">
        <button style="margin-top: 1rem;" class="toggle-visibility2" data-target="#post-detailsxxx">
            Créer un nouveau Topic
        </button> 
<!--Formulaire-->
<div id="post-detailsxxx" style="width: 40rem;">
    <form method="POST" role="form">   
        <div class="form-group"> 
            <label for="input_titre">Titre : </label>
	    <input class="form-control" type="text" id="input_titre" name="titre_topic" />
        </div>
        <div class="form-group"> 
            <label for="input_categorie">Catégorie : </label>
            <input class="form-control" type="text" id="input_categorie" name="categorie_topic" />
        </div>
        <!--
        <div class="form-group"> 
            <label for="input_posteur_topic">Auteur : </label>
            <input class="form-control" type="text" id="input_auteur" name="auteur_topic" />
        </div>
        -->
        <div class="form-group">
            <input class="form_button" name="submit" type="submit" value="Enregistrer" />
            <input class="form_button" name="Reset" type="submit" value="Effacer" />
        </div>  
    </form>
</div>
</div></div>
<?php
echo '<div class="table-responsive" style="margin-top: 2rem;"><table class="table" style="background: linear-gradient(white, #E6F3F7);">';
foreach($tabTopics as $topic) {
    echo '<tr><td ><!--' . 
          $topic->getIdCat(). '</td><td>' .' / -->' .
            
          '<a href=post.php?idtopic='.$topic->getIdTopic().'>'.$topic->getTitreTopic().'</a></td>' . 
          '<td>' .' créé(e) par : ' . '</td>' . 
          '<td>' . $topic->getIdUser().' '.$topicRepo->getPseudoByTopic($topic->getIdTopic()).'</td><tr/>'; 
}
echo '</div></table>';
?> 

		<?php
			echo $error_msg;
//                        echo $categories;
                        //var_dump($newTopic);
		?>

<?php
require_once('parts/footer.inc');
?>