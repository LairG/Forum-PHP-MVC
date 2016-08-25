<?php
require_once('parts/header.inc');

?>
<section style="display: inline-block; width: 100rem;">
<div class="navbar navbar-default navbar-static">
<div style="width: 65rem;">
    <form method="POST" role="form" style="margin-left: 35rem; ">   
        <div class="form-group"> 
			<label for="pseudo" id="label_pseudo">Votre pseudo</label> :
			<input class="form-control" type="text" name="pseudo" id="pseudo" value="<?php if(!$form_ok) echo $pseudo; ?>"/>
        </div>
        <div class="form-group"> 
			<label for="mdp1" id="label_mdp1">Votre mot de passe</label> :
			<input class="form-control" type="password" name="mdp1" id="mdp1"/>
		</div>
        <div class="form-group"> 
			<label for="mdp2" id="label_mdp2">Confirmer le mot de passe</label> :
			<input class="form-control" type="password" name="mdp2" id="mdp2"/>
		</div>
        <div class="form-group"> 
			<label for="nom" id="label_nom">Votre nom</label> :
			<input class="form-control" type="text" name="nom" id="nom" value="<?php if(!$form_ok) echo $nom; ?>"/>
		</div>
        <div class="form-group"> 
			<label for="prenom" id="label_prenom">Votre prénom</label> :
			<input class="form-control" type="text" name="prenom" id="prenom" value="<?php if(!$form_ok) echo $prenom; ?>"/>
		</div>
        <div class="form-group"> 
			<label for="tel" id="label_tel">Numéro de téléphone</label> :
			<input class="form-control" type="tel" name="tel" id="tel" value="<?php if(!$form_ok) echo $tel; ?>"/>
		</div>
        <div class="form-group"> 
			<label for="nais" id="label_nais">Date de naissance</label> :
			<input class="form-control" type="date" name="nais" id="nais" value="<?php if(!$form_ok) echo $nais; ?>"/>
		</div>
        <div class="form-group"> 
			<label for="email" id="label_email">Email</label> :
			<input class="form-control" type="text" name="email" id="email" value="<?php if(!$form_ok) echo $email; ?>"/>
		</div>	
        <div class="form-group" style="width: 18rem; display: inline;"> 
            <input style="background-color: #F05678;" class="form-control" type="reset" value="Remettre à zéro" />
            <input style="background-color: #B7F59A;" class="form-control" type="submit" value="S'inscrire" name="submit"/>
        </div>

		<p>
		<?php echo $errorMsg; ?>
		</p>

    </form>
</div>
</div>
</section>
<?php
require_once('parts/footer.inc');
?>