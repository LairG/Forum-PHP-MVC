<?php
require_once('parts/header.inc');

?>
<section style="display: inline-block; width: 100rem;">
<div class="navbar navbar-default navbar-static">
    <div style="width: 65rem;">
        <form method="POST" role="form" style="margin-left: 35rem;"> 
		<div class="form-group">
			<label for="input_pseudo">Pseudo : </label>
			<input class="form-control" type="text" id="input_pseudo" name="pseudo" />
		</div>
		<div class="form-group">
			<label for="input_mdp">Mot de passe : </label>
			<input class="form-control" type="password" id="input_mdp" name="mdp" />
		</div>
		<div class="form-group">
			<input style="background-color: #B7F59A;" class="form-control" class="form_button" name="submit" type="submit" value="Connexion" />
		</div>
		<?php
			echo $errorMsg;
		?>
	</form>
</section>
<?php
require_once('parts/footer.inc');
?>
