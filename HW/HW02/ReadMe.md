# VCS
	 VCS (버전관리 시스템)
	 일 변화를 시간에 따라 기록했다가 나중에 특정 시점의 버전을 다시 불러올 수 있는 시스템을 의미


# DVCS 와 VCS의 차이
* VCS    
	 로컬 버전관리 시스템으로 DB를 사용하여 파일의 변경 정보를 관리    
	 사진 : P01
     
* DVCS        
	 분산 버전관리 시스템       
	 일의 마지막 스냅샷을 checkout하지 않고 히스토리를 포함한 저장소를 복제       
	 서버에 문제가 생기면 복제물로 다시 작업을 할 수 있고 서버를 복원 가능       
	 많은 remote저장소를 가질 수 있기 떄문에 협업이 수월       
	 사진 : P02              
       
       
# GIT       
* repository 생성하기       
	1. Top Repositories 옆에 있는 초록색 버튼 NEW를 누른다.        
	2. Create a new repository 에서 Repository name
을 입력하고 PUBLIC / PRIVATE 을 선택하여 저장소를 만든다.       
	* 사진 : P09       
       
* GIT BASH repository 연결 과정       
	1. 파일을 만든 후 git init       
	  현재 디렉토리를 Git 저장소로 초기화합니다. 이 명령을 실행하면 Git은 해당 디렉토리에 .git이라는 숨겨진 폴더를 생성하여 버전 관리를 시작       
	2. git branch -m main       
	  현재 브랜치의 이름을 변경합니다. 이 경우, 기존의 브랜치 이름을 'main'으로 변경합니다. 이 명령을 통해 브랜치 이름을 변경 가능       
	3. git remote add 202327047 https://github.com/parksobin/202327047.git       
	  원격 저장소를 추가합니다. '202327047'라는 이름으로 지정된 원격 저장소를 추가하고, 해당 저장소의 URL은 https://github.com/parksobin/202327047.git입니다. 이제 이 원격 저장소에 있는 리모트 브랜치를 추적하거나 푸시        
	* 사진 : P04 ~ P08       
       
       
# gitignore        
* 사용법       
	1. git init 한 폴더에 .gitignore 이라는 이름 파일 생성.       
	2. 그 안에 한줄씩 제외할 파일 혹은 폴더 작성       
	3. 한줄씩 작성       
       
* 작성방식       
	1. fileName.js       
	특정 파일 fileName 제외하기       
	2. /fileName.js       
	현재 경로에 있는 fileName_1 만 제외       
	3.node_module/       
	특정 폴더 node_module 안의 파일 다 제외하기       
	4. folder/my.txt       
	특정 경로의 특정 파일 제외하기       
	5. folder       
	특정 경로 아래의 모든 fileName_2 제외하기       
	6. *.txt       
	특정 확장자 파일 다 제외하기       
	7. !fileName.txt       
	예외 만들기       
       
       
# Mark Down 표기법       
* 글머리       
	  # This is a H1       
	  ## This is a H2       
	  ### This is a H3       
	  #### This is a H4       
	  ##### This is a H5       
	  ###### This is a H6       
       
* BlockQuote       
	  ">" 블럭 인용문자 이용       
       
* 순서있는 목록(번호)       
	  1. 2. 3.       
       
* 순서없는 목록(글머리 기호: *, +, - )       
	  * 빨강
	    * 녹색
	      * 파랑

	  + 빨강
	    + 녹색
	      + 파랑

	  - 빨강
	    - 녹색
	      - 파랑	  	  
       
* 코드블럭       
	  <pre><code>{code}</code></pre>이용       
	  코드블럭코드("```") 을 이용       
       
* 수평선       
	  <hr/>       
       
* 링크       
	  사용문법: [Title](link)       
       
* 이미지        
	  "![Alt text](/path/to/img.jpg)"       
       
* 강조       
	  *single asterisks*       
	  _single underscores_       
	  **double asterisks**       
	  __double underscores__       
	  ~~cancelline~~       


