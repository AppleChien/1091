// Initialize and add the map
var map;
var city_death_number = 0;
var city_img
var year;
var content;
var post_year;
function start()
{
  initMap;
  var box = document.getElementById("button");
  box.addEventListener("click",initMap,false);
}
window.addEventListener("load",start,false);
function initMap() {
    map = new google.maps.Map(document.getElementById('map'), {
    zoom: 7,
    center: {lat: 23.858987, lng:120.917631}
  });
    map.data.loadGeoJson('taiwancity.json');
    post_year = $("#year").val();
    year = $("#year").val() + "year";
    map.data.setStyle(
    {
      fillColor: '#f00',
      fillOpacity: 0
    });

    var infowindow = new google.maps.InfoWindow({
      content: ""
    });

    map.data.addListener("mouseover",function(event) {
      var content = event.feature.getProperty("name");
      infowindow.setContent(content);
      var city_img = "<img style = 'width:100%; height:350px;'" + "src = " + event.feature.getProperty(year) + ">";
      //alert(city_img);
      death_number(content,post_year);
      document.getElementById('output').innerHTML = city_img + "<br>"+ "死亡人數:" + city_death_number;
      infowindow.setPosition(event.latLng);
      infowindow.open(map);
      map.data.revertStyle();
      map.data.overrideStyle(event.feature, {fillOpacity: 0.5});
    });
    map.data.addListener("mouseout",function(event) {
      infowindow.close();
      map.data.revertStyle();
      map.data.overrideStyle(event.feature, {fillOpacity: 0});
      document.getElementById('output').innerHTML = '';
    });
}
function death_number(cdata, ydata)
{
  $.ajax({
      url: "death_number.php",
      data:{
        pyear: ydata,
        city: cdata,
          },
      async:false,
      type: "POST",
      dataType: "html",
      success: function(output)
      {
        city_death_number = output;
      },
      error: function()
      {
          alert("qq");
      }
  });
}

