import { Component, OnInit, ViewChild } from '@angular/core';
import { FormBuilder, FormGroup } from '@angular/forms';
import { MatDialog, MAT_DIALOG_DATA } from '@angular/material';
import { DataService } from '../../services/data.service';
import { NotificationsService } from '../../services/notification.service';

@Component({
  selector: 'app-import-files',
  templateUrl: './import-files.component.html',
  styleUrls: ['./import-files.component.css']
})
export class ImportFilesComponent implements OnInit {

  @ViewChild('uploader', {static: true}) myInputVariable;

  public message: any = {};
  public document: Array<any> = [{}];
  public uploadForm: FormGroup;
  public fileName: string;
  public buttonEnable: boolean;
  public updateTimes: number;
  public top: number;
  public formData: FormData;

  constructor(
    private formBuilder: FormBuilder,
    private notification: NotificationsService,
    private data: DataService
  ) { }

  ngOnInit() {
    this.formData = new FormData();
    this.updateTimes = 0;
    this.top = 3;
    this.uploadForm = this.formBuilder.group({ profile: [''] });
    this.fileName = '';
    this.buttonEnable = false;
    this.message = {};

  }

  uploadFile($event) {
    const files = $event.target.files;
    for (const file of files) { this.formData.append('net_files', file); }
    this.buttonEnable = true;
    this.myInputVariable.nativeElement.value = '';
  }

  async onSubmit() {
    this.formData.append('net_files', this.uploadForm.get('profile').value);
    this.notification.info('Espere a que se terminen de procesar los archivos', 'Procesando archivos');
    this.data.addFiles(this.formData)
      .subscribe(
        async (data: any) => {
          this.document = data.err.mesg;
          switch (data.status) {
            case 'error': {
              if (this.document.length === 1) {
                this.notification.error(this.document[0], 'Error');
              }
              this.buttonEnable = false;
              this.fileName = '';
              break;
            }
            case 'success': {
              for (const name of data.data.info) {
                this.notification.success(name, 'Agregado exitosamente el documento');
              }
              this.message = { msg: 'Success' };
              this.buttonEnable = false;
              this.fileName = '';
              break;
            }
            case 'warning': {
              this.document = data.err.mesg;
              this.notification.warn(this.document, data.status);
              this.buttonEnable = false;
              this.fileName = '';
              break;
            }
            default: break;
          }
        });
    this.formData = new FormData();
  }


}
