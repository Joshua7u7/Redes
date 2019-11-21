import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { environment } from 'src/environments/environment';
import {HttpResponse} from '@angular/common/http';

@Injectable({
  providedIn: 'root'
})
export class DataService {

  constructor(private http: HttpClient) { }

  addFiles(formData) {
    return this.http.post(environment.API + '/documents/files', formData);
  }

  getFile(filename: string) {
    return this.http.get(environment.API + '/documents/get/file/' + filename).toPromise();
  }

  downloadFile(filename: string) {
    return this.http.get(environment.API + '/documents/get/file/' + filename, {responseType: 'arraybuffer'});
   }
}
