<?php
require_once('parts/header.inc');

?>

<!--Bouton permettant le hide/show du formulaire-->
<div class="navbar navbar-default navbar-static">
    <div class="container">
        <button style="margin-top: 1rem;" class="toggle-visibility" data-target="#post-detailsxxx">
            Créer un nouveau Post
        </button>                       

<!--Formulaire d'insertion de nouveau Post-->
<div id="post-detailsxxx" <?php if(empty($tmpId_Post)) { echo 'style="display: none;"'; } ?>>
    <form method="POST" role="form">   
        <div class="form-group"> 
            <input type="text" name="champs_vide" hidden value="<?php echo $tmpId_Post?>" id="auteur_post"/> <!--hidden="none" -->
        </div>

        <div class="form-group">
            <label for="auteur_post">Auteur:</label>
            <input class="form-control" type="text" name="auteur_post" value="<?php echo $tmpIdUser?>" id="auteur_post"/>
        </div>
         <div class="form-group">
            <label for="nouvelle_date_post">Date :</label>
            <input class="form-control" type="datetime" name="nouvelle_date_post" value="<?php echo $tmpDate?>" id="nouvelle_date_post"/>
         </div>
         <div class="form-group">
            <label for="contenu_post">Contenu :</label>
            <input class="form-control" type="textarea" name="contenu_post" value="<?php echo $tmpContenu?>"  id="input_contenu_post"/>
         </div>
         <div class="form-group">
            <input class="form-control" type="submit" name="submit_post" value="Valider">
         </div>    
    </form>
        </div>
    </div> 
</div>

<!--Select de pagination des pages-->
<div style="margin-left: 20rem; margin-top: 5rem;">
<select class="form-control" onChange="location = this.options[this.selectedIndex].value;" style="width: 100px;">
    <option>Choix</option>
    <option value='post.php?limite=5&idtopic=<?php echo $id_topic ?>' >5</option>
    <option value='post.php?limite=10&idtopic=<?php echo $id_topic ?>'>10</option>
    <option value='post.php?limite=15&idtopic=<?php echo $id_topic ?>'>15</option>
    <option value='post.php?limite=20&idtopic=<?php echo $id_topic ?>'>20</option>
</select>
</div>


<!--Affiche la liste des post déjà écrits-->
<?php
    echo $retourValeur;
    echo $paginationPost
?>

<?php
require_once('parts/footer.inc');

?>
