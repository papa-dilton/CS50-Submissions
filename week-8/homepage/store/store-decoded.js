if (getCookie("gtaEnabled") == "true") {
    addGTA();
}

function getCookie(name) {
    name += "=";
    const cookieArray = document.cookie.split("; ");
    let toReturn;
    cookieArray.forEach((value) => {
        if (value.indexOf(name) == 0) toReturn = value.substring(name.length);
    });
    return toReturn;
}

function addGTA() {
    if (getCookie("gtaEnabled") != "true") {
        gtaBut = document.createElement("li");
        gtaBut.innerHTML = '<button class="selector">GTA VI</button>';
        gtaBut.setAttribute('id', 'gtaBut')
        document.querySelector(".but-row ul").append(gtaBut)
        document.querySelector("#gtaBut").addEventListener('click', function() {
            if (document.getElementById('store-item-gta6').style.display == 'none') {
                document.getElementById('store-item-gta6').style.display == 'contents'
            } else {
                document.getElementById('store-item-gta6').style.display == 'none'
            }
        })
        gtaBut.addEventListener("click", function() {
            document.querySelector(".carousel").innerHTML = "<div id='store-item-gta6'><video width='100%' height='auto' controls><source src='gta6-trailer.mp4' type='video/mp4'>    <source src='gta6-trailer.ogg' type='video/ogg'>  <h1 style='color: white;'>Please upgrade your browser to view the video</h1>  </video><img src='gta6-cover.png' id='vert-cover'><div class='textbox'>    <h4>Grand Theft Auto VI</h4>    <p>It's finally here. A drop so huge, even we had to hide it. A long-awaited sequel to one of, if not the, most successful games in history. Bring your biggest, baddest plays to this new edition, with levels of drugs, money, and lies never seen before. There is no better way to feel like a kingpin than completing an 18kg drop-off while being chased by maniacs in a rocket-armed helicopter Buy now for PC.</p></div><div><button class='buy-but'>$420</button></div><img src='gta6-cover2.webp' id='horz-cover'></div>";
        });
        document.cookie = "gtaEnabled=true";
        var head = document.getElementsByTagName("HEAD")[0];
        var link = document.createElement("style");
        link.type = "text/css";
        link.innerHTML =
            "#store-item-gta6 #vert-cover {        width: 40%;        float: left;    }        #store-item-gta6 .textbox {        color: white;        float: left;        width: 55%;        margin-left: 40px;    }        #store-item-gta6 .buy-but {        float: left;        margin-left: 40px;        width: 55%;    }        #store-item-gta6 #horz-cover {        width: 100%;    }        @media only screen and (max-width:920px) {        #store-item-gta6 #vert-cover {            width: 80%;            margin-left: 10%;            margin-right: 10%;        }                #store-item-gta6 .textbox {            color: white;            float: left;            width: 80%;            margin-left: 10%;        }                #store-item-gta6 .buy-but {            float: left;            margin-left: 10%;            width: 80%;        }    }";
        head.appendChild(link);
        return "Page ready for GTA. Run 'removeGTA()' to remove.";
    } else {
        return "GTA is already enabled."
    }
}

function removeGTA() {
    document.cookie = "gtaEnabled=false";
    location.reload(false);
    return "cookie for GTA removed.";
}

// obfuscator - https://www.obfuscator.io/