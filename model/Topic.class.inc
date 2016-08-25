<?php
class Topic {
	private $idTopic;
        private $titreTopic;
        private $idUser;
        private $idCat;
        
        public function __construct($idTopic, $titreTopic, $idUser, $idCat) {
            $this->setIdTopic($idTopic);
            $this->setTitreTopic($titreTopic);
            $this->setIdUser($idUser);
            $this->setIdCat($idCat);
    
	
        }
	public function getIdTopic() {
		return $this->idTopic;
	}
	
	private function setIdTopic($idTopic) {
		if(is_int($idTopic)) {
			$this->idTopic = $idTopic;
		} else {
			throw new Exception('L\'id du topic doit être un entier');
		}
	}

        public function getTitreTopic() {
		return $this->titreTopic;
	}
	
	public function setTitreTopic($titreTopic) {
		$titreTopic = trim($titreTopic);
		$titreTopic = strip_tags($titreTopic);
		if(is_string($titreTopic) && $titreTopic != '') {
			$this->titreTopic = substr($titreTopic, 0, 49);
		} else {
			throw new Exception('Le titre de l\'article doit être une chaine non vide');
		}
	}
        
        public function getIdUser() {
		return $this->idUser;
	}
	
	public function setIdUser($idUser) {
		if(is_int($idUser)) {
			$this->idUser = $idUser;
		} else {
			throw new Exception('L\'id du user doit être un entier');
		}
	}
        
        public function getIdCat() {
		return $this->idCat;
	}
	
	private function setIdCat($idCat) {
		if(is_int($idCat)) {
			$this->idCat = $idCat;
		} else {
			throw new Exception('L\'id de la catégorie doit être un entier');
		}
	}
}