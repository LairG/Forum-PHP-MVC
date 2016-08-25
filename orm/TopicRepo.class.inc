<?php
require_once('orm/AbstractRepo.class.inc');
require_once('orm/UserRepo.class.inc');
require_once('model/Topic.class.inc');

class TopicRepo extends AbstractRepo {
	private static $instance;
	
	public static function getInstance() {
		if(isset(self::$instance)) {
			return self::$instance;
		} else {
			self::$instance = new TopicRepo();
			return self::$instance;
		}
	}
	
	protected function __construct() {
		parent:: __construct();
	}

        
	public function getAllTopicsByCategorieId($cat_id) {
//Va afficher la liste des topics deja dispo
           // $sql = 'SELECT * FROM topic a NATURAL JOIN user u ORDER BY topic DESC;';
	$sql = 'SELECT * FROM topic WHERE id_categorie=:varIdCat;';
		$st  = $this->getDb()->prepare($sql);
                
                $params = array(
                    'varIdCat' => $cat_id,
                );
                
                $st->execute($params);
		
		$tabTopic = array();
                
		while($topicTmp = $st->fetch()) {
				//var_dump($topicTmp);
			$tabTopic[] = new Topic(intval($topicTmp['id_topic']), $topicTmp['titre'], intval($topicTmp['id_user']),intval($topicTmp['id_categorie']));
	}
        //var_dump($tabTopic);
        return $tabTopic;}
        
	public function getPseudoByTopic($idTopic){
            $sql="SELECT pseudo FROM topic INNER JOIN user ON topic.id_user = user.id_user
                  WHERE id_topic = $idTopic;";
            $result = $this->getDb()->query($sql);
            
            $pseudoUserTopic = $result->fetch(); 
            return $pseudoUserTopic['0'];
        }
        
public function save($topic) {
//Va sauvegarder chaque nouveau topic créé		
             $sql = "INSERT INTO topic(titre, id_user, id_categorie) VALUES(:varTitreTopic, :varIdUser, :varIdCategorie);";
		
		$st = $this->getDb()->prepare($sql);
		
		$params = array(
			'varTitreTopic' => $topic->getTitreTopic(),
                        'varIdUser' => $topic->getIdUser(),
                        'varIdCategorie' => $topic->getIdCat(),
                    
			
		);
		
		$st->execute($params);
	}
}
?>

<?php 
/*
// on se connecte à MySQL 
$db = mysql_connect('172.26.10.110', 'admin', ''); 

// on sélectionne la base 
mysql_select_db('forum',$db); 

// on crée la requête SQL 
$sql = 'SELECT (select titre from categorie where topic.id_categorie = categorie.id_categorie)as titre_cat, id_categorie,titre,(select prenom from user where topic.id_user = user.id_user) as id_user FROM topic'; 

// on envoie la requête 
$req = mysql_query($sql) or die('Erreur SQL !<br>'.$sql.'<br>'.mysql_error()); 

// on fait une boucle qui va faire un tour pour chaque enregistrement 
while($data = mysql_fetch_assoc($req)) 
    { 
    // on affiche les informations de l'enregistrement en cours 
    echo '<h4><b>'.$data['titre_cat'].' / '.$data['titre'].' créé(e) par : '.$data['id_user'].'</b><h4/>'; 
    
    } 

// on ferme la connexion à mysql 
mysql_close(); 
  
 */
?>
