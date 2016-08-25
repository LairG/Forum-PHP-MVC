<?php
require_once('orm/AbstractRepo.class.inc');
require_once('model/Post.class.inc');

class PostEditRepo extends AbstractRepo {
    private static $instance;
    
    public static function getInstance() {
		if(isset(self::$instance)) {
			return self::$instance;
		} else {
			self::$instance = new PostEditRepo();
			return self::$instance;
		}
	}
        
    protected function __construct() {
		parent::__construct();
    }    
    
    public function insertPost($post){
        
        $sqlInsert = 'INSERT INTO post(id_post, contenu, date_post, id_user, id_topic) VALUES(:idPost, :contenu, :datePost, :idUser, :idTopic);';
        $params = array(
			'idPost' => $post->getIdPost(),
			'contenu' => $post->getContenuPost(),
			'datePost' => $post->getDatePost('iso'),
			'idUser' => $post->getAuteurPost()->getIdUser(),
			'idTopic' => $post->getTopic()->getIdTopic()
		);
        $st = $this->getDb()->prepare($sqlInsert);
        $st->execute($params);
    }
    
    public function updatePost($post){
       
        $sqlUpdate = 'UPDATE post SET contenu=:contenu, date_post=:date_post, id_user=:id_user, id_topic=:id_topic WHERE id_post=:id_post;';
        //var_dump($post);
        //var_dump($post->getContenuPost());
        $params = array(
			'id_post' => $post->getIdPost(),
			'contenu' => $post->getContenuPost(),
			'date_post' => $post->getDatePost('iso'),
			'id_user' => $post->getAuteurPost()->getIdUser(),
                        'id_topic' => $post->getTopic()->getIdTopic()
		);
        var_dump($params);  
         
        $st = $this->getDb()->prepare($sqlUpdate);
        $st->execute($params);
        var_dump($st);
        //$res = $st->fetch();
        //var_dump($res);
    }
}//--------------->class PostEditRepo
?>