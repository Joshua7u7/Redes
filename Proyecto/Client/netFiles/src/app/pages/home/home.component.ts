import { Component, OnInit } from '@angular/core';
import { DataService } from '../../services/data.service';

@Component({
  selector: 'app-home',
  templateUrl: './home.component.html',
  styleUrls: ['./home.component.css']
})
export class HomeComponent implements OnInit {

  constructor(private data: DataService) { }

  ngOnInit() {
  }

  getFile() {
    const Filename = prompt('Nombre del archivo', 'recuerda poner su extensión');

    this.data.downloadFile(Filename).subscribe((data: any) => {
      this.writeContents(data, Filename, 'text/txt');
    });
  }

  writeContents(content, fileName, contentType) {
    const a = document.createElement('a');
    const file = new Blob([content], {type: contentType});
    a.href = URL.createObjectURL(file);
    a.download = fileName;
    a.click();
  }

}
