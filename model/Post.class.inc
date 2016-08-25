<?php



class Post{
    private $idPost;
    private $auteurPost;
    private $topic;
    private $datePost;
    private $contenuPost;
    
    public function __construct($idPost, $auteurPost, $topic, $datePost, $contenuPost) {
        $this->setIdPost($idPost);
        $this->setAuteurPost($auteurPost);
        $this->setTopic($topic);
        $this->setDatePost($datePost);
        $this->setContenuPost($contenuPost);
    }
    
    public function getIdPost(){
        return $this->idPost;
    }
    
    public function setIdPost($idPost){
        if(is_int($idPost)) {
		$this->idPost = $idPost;
	} else {
		throw new Exception('L\'id du post doit être un entier');
	}
    }
    
     public function getAuteurPost(){
        return $this->auteurPost;
    }
    
    public function setAuteurPost($auteurPost){
        if(is_a($auteurPost, 'User')) {
		$this->auteurPost = $auteurPost;
	} else {
		throw new Exception('L\'auteur doit être un objet instance de la classe User !');
	}
    }
    
     public function getTopic(){
        return $this->topic;
    }
    
     public function setTopic($topic){
        if(is_a($topic, 'Topic')) {
		$this->topic = $topic;
	} else {
		throw new Exception('Le topic doit être un objet de la classe Topic !');
	}
    }
    
     public function getDatePost($lang=fr){
         switch($lang) {
			case 'iso':
				return $this->datePost;
				break;
			case 'fr':
			default:
				return date_format(date_create($this->datePost), 'd/m/Y');
		}
    }
    
     public function setDatePost($datePost){
      $datePost = trim($datePost);
		//$datePost = $this->dateFR2ISO($datePost);
		//if($datePost) {
			$this->datePost = $datePost;
		//} else {
		//	throw new Exception('La date ' . $datePost . ' n\'est pas correcte');
		//}
    }
    
    private function checkDateISO($dateISO) {
		$motif = '#^([0-9]{4})-([01]?[0-9])-([0-2]?[0-9]|3[01])$#';
		
		if(preg_match($motif, $dateISO)) {
			$tabDate = explode('-', $dateISO);
			return checkdate($tabDate[1], $tabDate[2], $tabDate[0]);
		} else {
			return false;
		}
	}
	
	private function dateFR2ISO($dateFR) {
		if(strpos($dateFR, ' ')) {
			$dateFR = substr($dateFR, 0, strpos($dateFR, ' '));
		}
		$motif = '#^([0-2]?[0-9]|3[01])/([01]?[0-9])/([0-9]{4})$#';
		$replace = '$3-$2-$1';
		
		$dateISO = preg_replace($motif, $replace, $dateFR);
		
		if(!$this->checkDateISO($dateISO)) {
			return false;
		} else {
			return $dateISO;
		}
	}
    
     public function getContenuPost(){
        return $this->contenuPost;
    }
    
    public function setContenuPost($contenuPost){
        $contenuPost = trim($contenuPost);
        $contenuPost = strip_tags($contenuPost, '<b><strong><i><em><u><ul><li><ol>');
        //$contenuPost = str_replace(' ', '&nbsp;', $contenuPost);
	$contenuPost = nl2br($contenuPost);
	if(is_string($contenuPost) && $contenuPost != '') {
		$this->contenuPost = $contenuPost;
	} else {
		throw new Exception('Le contenu du post ne doit être une chaine non vide');
	}
    }
    
}//--------------->class Post

?>