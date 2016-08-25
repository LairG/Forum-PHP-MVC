<?php
require_once('orm/TopicRepo.class.inc');
//require_once('orm/AbstractRepo.class.inc');
require_once('orm/PostAffDeleteRepo.class.inc');
 if(isset($_SESSION['loggedUser'])) {
		$loggedUser = unserialize($_SESSION['loggedUser']);
	} else {
		$loggedUser = false;
	}       
        
$titreTopic = (isset($_POST['titre_topic']))?($_POST['titre_topic']):('');
/*$idAuteur = (isset($_POST['auteur_topic']))?($_POST['auteur_topic']):('');*/
$idCategorie = (isset($_POST['categorie_topic']))?($_POST['categorie_topic']):('');
$submit_ok = isset($_POST['submit']);
/*$submit_fail = isset($_POST['reset']); (ligne créée par amandine)*/

$error_msg = '';
//var_dump($titreTopic);
/*/update ou insert dans la bd, selon le "idTopic"*/
if($submit_ok) {
    /*var_dump($loggedUser);*/
    try {
            //$topicRepo = TopicRepo::getInstance();
            $newTopic = new Topic(-1,$titreTopic,$loggedUser->getIdUser(),(int)$idCategorie);
            $topicRepo = TopicRepo::getInstance();
            $topicRepo->save($newTopic);
//            
  /*          // on se connecte à MySQL 
            $db = mysql_connect('172.26.10.110', 'admin', ''); 

            // on sélectionne la base 
            mysql_select_db('forum',$db); 

            // on crée la requête SQL 
            $sql = "INSERT INTO forum.topic(titre,id_user,id_categorie) values ('$titreTopic',$idAuteur,1);"; 

            // on envoie la requête 
            $req = mysql_query($sql) or die('Erreur SQL !<br>'.$sql.'<br>'.mysql_error()); 

            // on fait une boucle qui va faire un tour pour chaque enregistrement 


            // on ferme la connexion à mysql 
            mysql_close();
    */        
            if($titreTopic){
               // $topicRepo->insertTopic($newTopic); 
                // est-ce qu'il existe déjà ?
                // todo
               // $topicRepo->updateTopic($newTopic);
            } 
            else {
            }           
    } catch(Exception $e) {
            $error_msg .= $e->getMessage();
    }
    
}

//if($submit_ok) {
//		try {
//			$newArticle = new Article(-1, $titreArticle, $dateArticle, $corpsArticle, $loggedUser);
//			$articleRepo = ArticleRepo::getInstance();
//			
//			$articleRepo->save($newArticle);
//		} catch(Exception $e) {
//			$error_msg .= $e->getMessage();
//		}
//	}

//Affichage de l'ensemble des topics
//$idcat = (isset($_GET['idcat']))?($_GET['idcat']):('');

if(isset($_GET['idcat'])) {
    $topicRepo = TopicRepo::getInstance();
    $tabTopics = $topicRepo->getAllTopicsByCategorieId($_GET['idcat']);
} else {
    header('Location: index.php');
}
?>
