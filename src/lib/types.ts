export interface FileMetadataType {
  name?: string;
  modified_time?: Date;
  size?: number; // Size in bytes, optional for directories
  [key: string]: unknown; // Allow additional properties
}

export interface CodeFileType extends FileMetadataType {
  status?: "AC" | "WA" | "TLE" | "RE" | "CE";
  submit_time?: Date; // Time when the code was submitted
}

export interface ProblemInfoType {
  rel_path: string;
  name?: string;
  link?: string;
  solved?: boolean;
  solved_in_contest?: boolean;
  files: FileMetadataType[];
  [key: string]: unknown; // Allow additional properties
}

export interface ContestInfoType {
  rel_path: string;
  link?: string;
  date: string;
  name: string;
  start_time?: Date;
  end_time?: Date;
  platform: string;
  problems: ProblemInfoType[];
  files: FileMetadataType[];
  [key: string]: unknown; // Allow additional properties
}
