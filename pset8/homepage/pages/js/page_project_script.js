// checks the time and presents the photo according to period

function load() {
    // getting the HTML elements
    var msg = window.document.getElementById('msg')
    var img = window.document.getElementById('image')
    var lnk = window.document.getElementById('link')
    var select = document.getElementById('select');
	  var value = select.options[select.selectedIndex].value;

    //inject a message on the screen
    msg.innerHTML = `Access <strong>Pset ${value}</strong> clicking on the image.`

    // checks which week was chosen and presents an image and a link
    switch(value) {
        case "0":
            lnk.href = 'https://cs50.harvard.edu/x/2020/psets/0/'
            img.src = './images/week0.png'
            document.body.style.background = '#351104'
          break;
        case "1":
            lnk.href = 'https://cs50.harvard.edu/x/2020/psets/1/'
            img.src = './images/week1.png'
            document.body.style.background = '#287EF8'
          break;
        case "2":
            lnk.href = 'https://cs50.harvard.edu/x/2020/psets/2/'
            img.src = './images/week2.png'
            document.body.style.background = '#D68E31'
          break;
        case "3":
            lnk.href = 'https://cs50.harvard.edu/x/2020/psets/3/'
            img.src = './images/week3.png'
            document.body.style.background = '#BDA498'
          break;
        case "4":
            lnk.href = 'https://cs50.harvard.edu/x/2020/psets/4/'
            img.src = './images/week4.png'
            document.body.style.background = '#464945'
          break;        
        case "5":
            lnk.href = 'https://cs50.harvard.edu/x/2020/psets/5/'
            img.src = './images/week5.png'
            document.body.style.background = '#8F251E'
          break;        
        case "6":
            lnk.href = 'https://cs50.harvard.edu/x/2020/psets/6/'
            img.src = './images/week6.png'
            document.body.style.background = '#70906F'
          break;  
        case "7":
            lnk.href = 'https://cs50.harvard.edu/x/2020/psets/7/'
            img.src = './images/week7.png'
            document.body.style.background = '#53370D'
          break;          
        default:
            // week 8
            lnk.href = 'https://cs50.harvard.edu/x/2020/tracks/'
            img.src = './images/week8.png'
            document.body.style.background = '#090E1B'
      }
}