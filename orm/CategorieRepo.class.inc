<?php
require_once('model/Categorie.class.inc');
class CategorieRepo extends AbstractRepo {
	private static $instance;
	
	public static function getInstance() {
		if(isset(self::$instance)) {
			return self::$instance;
		} else {
			self::$instance = new CategorieRepo();
			return self::$instance;
		}
	}
	
	protected function __construct() {
		parent::__construct();
	}
        //select categories
        public function getCategorieById(){
            
            $sql = 'SELECT * FROM categorie c NATURAL JOIN user u ORDER BY id_categorie DESC;';
            $result = $this->getDb()->query($sql);
		
            while($catTmp = $result->fetch()){
                
                
                
                $tabCategorie[] = new Categorie($catTmp['id_categorie'],$catTmp['titre'],$catTmp['description'],
                        $catTmp['id_user']);
            }
            return $tabCategorie;
            
        }
        //insert categorie
        public function saveCategorie($categorie){
            $sql = 'INSERT INTO categorie(titre, description, idAuteur) VALUES (:titre, :description, :idAuteur);';
            $st = $this->getDb()->prepare($sql);

        $params = array(
            'titre' => $categorie->getTitreCategorie(),
            'description' => $categorie->getDescriptionCategorie(),
            'idAuteur' => $categorie->getIdAuteur(),
        );

        $st->execute($params);
        }
        //Delete categorie
        public function supCategorie($param) {
            $sql ='DELETE FROM categorie WHERE id_categorie = $param ;';
             $st = $this->getDb()->prepare($sql);
             $st->execute($param);
        }
        //fonctions de recup des nom user
        
        public function getPseudoUserCategorie($id_categorie){
            $sql ="SELECT pseudo FROM categorie INNER JOIN user ON user.id_user = categorie.id_user WHERE id_categorie = $id_categorie";
            $result = $this->getDb()->query($sql);
            
            $pseudoUserCat = $result->fetch(); 
            return $pseudoUserCat['0'];
        }
        
        public function getPseudoLastPost($id_categorie){
            $sql ="SELECT pseudo FROM vue_complete
                    INNER JOIN user on vue_complete.id_user_post = user.id_user
                     WHERE id_categorie = $id_categorie
                     ORDER BY date_post DESC LIMIT 1";
            $result = $this->getDb()->query($sql);
            
            $pseudoLastPost = $result->fetch(); 
            return $pseudoLastPost['0'];
        }
        
        
        //fonctions de calcul 
        //date dernier post par categorie
        public function getDatelastPost($id_categorie){
            $sql="SELECT max(date_post) FROM vue_complete WHERE id_categorie = $id_categorie";
            $result = $this->getDb()->query($sql);
            
            $dateLastPost = $result->fetch(); 
            return $dateLastPost['0'];
        }
        
        //nb de posts par categorie
        public function getNbPosts($id_categorie){
            $sql="SELECT count(id_post) FROM vue_complete WHERE id_categorie = $id_categorie";
            $result = $this->getDb()->query($sql);
            
            $nbPost = $result->fetch(); 
            return $nbPost['0'];
        }
        
        //nb de topics par categorie
        public function getNbTopics($id_categorie){
            $sql="SELECT count(id_topic) FROM topic WHERE id_categorie = $id_categorie";
            $result = $this->getDb()->query($sql);
            
            $nbTopic = $result->fetch(); 
            return $nbTopic['0'];
        }
}