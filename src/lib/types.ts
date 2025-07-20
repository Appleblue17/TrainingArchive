export type FileMetadataType = {
  name?: string;
  modified_time?: Date;
  size?: number; // Size in bytes, optional for directories
  [key: string]: unknown; // Allow additional properties
};

export type ProblemInfoType = {
  rel_path: string;
  name?: string;
  link?: string;
  solved?: boolean;
  solved_in_contest?: boolean;
  files: FileMetadataType[];
  [key: string]: unknown; // Allow additional properties
};

export type ContestInfoType = {
  rel_path: string;
  link?: string;
  date: string;
  title: string;
  duration: string;
  platform: string;
  problems: ProblemInfoType[];
  files: FileMetadataType[];
  [key: string]: unknown; // Allow additional properties
};
