import { Request, Response } from "express";


class DocumentController {

  public receive (req: Request, res: Response) {
    const re: any = req;
    const files_names: Array<string> = new Array<string>();
    for (const name of re.files) {
      files_names.push(name.filename);
    }
    res.json({status: "success", err:{}, data:{info: files_names}});
  }
 
}

const documentController = new DocumentController();
export default documentController;